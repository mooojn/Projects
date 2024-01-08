import os,shutil 

dict_extensions={ 'audio_extensions' : ('.mp3','.m4a','.wav'),
                 'video_extensions' : ('.mp4','mkv','mpeg'),
                 'documents_extensions' : ('.jpg','.txt','.csv')}

path="D:\python_programs\projects\prj1"

def file_finder(folder_path,file_extensions):
    return [file for file in os.listdir(folder_path) 
                for extension in file_extensions 
                  if file.endswith(extension)]
for extension_type,extension_tuple in dict_extensions.items():
    # print(file_finder(folder_path,extension_tuple))
    found_files=file_finder(path,extension_tuple)
    if found_files:    
        folder_name=extension_type.split('_')[0].title()+'s'
        folder_path=os.path.join(path,folder_name)
        if os.path.exists(folder_path):
            pass
        else:
            os.mkdir(folder_path)
        
    for item in found_files:
        item_path=os.path.join(path,item)
        item_new_path=os.path.join(folder_path,item)
        shutil.move(item_path,item_new_path)
