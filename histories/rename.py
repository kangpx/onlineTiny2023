import os

def rename_files(root):
    for filename in os.listdir(root):
        if 'fullvalid' not in filename and 'partvalid' not in filename:
            new_filename = filename.split('.')[0] + '_partvalid.' + filename.split('.')[1]
            os.rename(os.path.join(root, filename), os.path.join(root, new_filename))

if __name__ == '__main__':
    rename_files('./ultra')
    rename_files('./qvar')
