import samweb_client as sam
import sqlite3
import argparse
from glob import glob
from tqdm import tqdm
import subprocess
import os.path

SUFF = '_lite.h5'

EXEC = '/exp/icarus/app/users/mueller/spineprod/cafmaker/spine_cafmaker/build/merge_sources_simulation'

CREATE_DB = """
CREATE TABLE IF NOT EXISTS dataset(
larcv_name text NOT NULL PRIMARY KEY,
parent_name text NOT NULL,
standard_name text,
hdf5_name text,
flat_name text,
flat_time integer DEFAULT 0
);
"""

def command(curs, comm, vals=None):
    """
    Execute a command defined in a string.

    Parameters
    ----------
    curs: The SQLite cursor handle.
    comm: The base command.
    vals: Values to use as arguments for the sql command (tuple).

    Returns
    -------
    None.
    """
    try:
        if isinstance(vals, list):
            curs.executemany(comm, vals)
        elif vals:
            curs.execute(comm, vals)
        else:
            curs.execute(comm)
    except Exception as e:
        print(e)

def main(definition, update, hdf5, flat):
    # Connect to the database.
    db_name = f'db/{definition}.db'
    conn = sqlite3.connect(db_name)
    curs = conn.cursor()
    command(curs, CREATE_DB)
    conn.commit()

    # Setup the SAMWeb client for access to definition information.
    samweb = sam.SAMWebClient()

    # Find LArCV files and add them to the table.
    if update:
        files = samweb.listFiles(defname=f'{definition}_larcv')
        pbar = tqdm(files)
        pbar.set_description('Looking up parent LArCV files')
        parentage = [samweb.getMetadata(m)['parents'][0]['file_name'] for m in pbar]
        ins = list(zip(files, parentage))
        command(curs, 'INSERT INTO dataset(larcv_name,parent_name) VALUES(?,?);', ins)
        conn.commit()

    # Find CAF files and add them to the table.
    if update:
        files = samweb.listFiles(defname=f'{definition}_caf')
        pbar = tqdm(files)
        pbar.set_description('Inserting parent CAF files')
        parentage = [samweb.getMetadata(m)['parents'][0]['file_name'] for m in pbar]
        ins = list(zip(files, parentage))
        command(curs, 'UPDATE dataset SET standard_name=? WHERE parent_name=?;', ins)
        conn.commit()

    # Find HDF5 files and add them to the table.
    if hdf5 is not None:
        files = glob(f'{hdf5}/*{SUFF}')
        print(os.path.basename(files[0])[:-len(SUFF)])
        pbar = tqdm(files)
        pbar.set_description('Inserting HDF5 files')
        for f in pbar:
            hdf5_name = os.path.basename(f)
            larcv_name = hdf5_name[:-len(SUFF)]+'.root'
            command(curs, 'UPDATE dataset SET hdf5_name=? WHERE larcv_name=?;', (hdf5_name, larcv_name))
        conn.commit()

    # Produce the flat files.
    if flat is not None and hdf5 is not None:
        command(curs, 'SELECT hdf5_name, standard_name FROM dataset WHERE flat_name IS NULL AND hdf5_name IS NOT NULL AND standard_name IS NOT NULL;')
        files = [x for x in curs.fetchall()]
        pbar = tqdm(files)
        pbar.set_description('Producing flat files')
        for f in pbar:
            hdf5_name = hdf5 + f[0]
            caf_name = samweb.locateFile(f[1])[0]['full_path'].split(':')[1] + '/' + f[1]
            flat_name = flat + f[0][:-len(SUFF)]+'_flat.root'
            subprocess.run([EXEC, './tmp.root', caf_name, hdf5_name], capture_output=True)
            subprocess.run(['flatten_caf', './tmp.root', flat_name], capture_output=True)
            time = os.path.getmtime(hdf5_name)
            command(curs, 'UPDATE dataset SET flat_name=?, flat_time=? WHERE hdf5_name=?;', (flat_name, time, f[0]))
        conn.commit()

        # Check for hdf5 files with modified time stamps newer than the flat files.
        command(curs, 'SELECT hdf5_name, standard_name, flat_time FROM dataset WHERE hdf5_name IS NOT NULL AND flat_name IS NOT NULL;')
        files = [(x[0], x[1]) for x in curs.fetchall() if os.path.getmtime(hdf5+x[0]) > x[2]]
        pbar = tqdm(files)
        pbar.set_description('Updating flat files')
        for f in pbar:
            hdf5_name = hdf5 + f[0]
            caf_name = samweb.locateFile(f[1])[0]['full_path'].split(':')[1] + '/' + f[1]
            flat_name = flat + f[0][:-len(SUFF)]+'_flat.root'
            subprocess.run([EXEC, './tmp.root', caf_name, hdf5_name], capture_output=True)
            subprocess.run(['flatten_caf', './tmp.root', flat_name], capture_output=True)
            time = os.path.getmtime(hdf5_name)
            command(curs, 'UPDATE dataset SET flat_name=?, flat_time=? WHERE hdf5_name=?;', (flat_name, time, f[0]))
        conn.commit()

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--definition', default=None)
    parser.add_argument('--update', default=False, action='store_true')
    parser.add_argument('--hdf5', default=None)
    parser.add_argument('--flat', default=None)
    args = parser.parse_args()
    main(args.definition, args.update, args.hdf5, args.flat)
