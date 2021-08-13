import os
path0 = r'E:\cup'
path1 = r'E:\temp'
for root,ds,filenames in os.walk(path0,followlinks=True):
    for filename in filenames:
        filepath=os.path.join(root,filename)
        file=open(filepath,"r+",encoding='UTF-8')
        newfile=open(filename,'w',encoding='UTF-8')
        for line in file.readlines():
            strs = line.strip().split(" ")
            strs[0]="2"
            newline='{0} {1} {2} {3} {4}\n'.format(strs[0], strs[1], strs[2], strs[3], strs[4])
            newfile.writelines(newline)
        print(filename)
        newfile.close()
        file.close    