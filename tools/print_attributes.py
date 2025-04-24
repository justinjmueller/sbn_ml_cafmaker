from argparse import ArgumentParser
import h5py

def main(filename, dataset=None):
    type_map = {'|u1': 'bool', '<i4': 'int32', '<i8': 'int64', '<f4': 'float', '<f8': 'double'}
    with h5py.File(filename, 'r') as f:
        if dataset is None:
            print('No dataset specified. Printing existing datasets:')
            for key in f.keys():
                print(key)
        else:
            res = {}
            count = -1
            for i in f[dataset].dtype.descr:
                if type(i[1]) == str and i[1] in type_map.keys():
                    res[i[0]] = type_map[i[1]]
                    if len(i) > 2:
                        res[i[0]] += f' {i[2]}'
                else:
                    res[i[0]] = i[1]
            for key in sorted(res):
                count += 1
                print(f'{key:<20}: {res[key]}')
            print(f'\n{count} attributes found.')

if __name__ == '__main__':
    parser = ArgumentParser(description='Print attributes of an HDF5 file or dataset')
    parser.add_argument('--filename', help='HDF5 file')
    parser.add_argument('--dataset', help='Dataset in HDF5 file')
    args = parser.parse_args()
    main(args.filename, args.dataset)