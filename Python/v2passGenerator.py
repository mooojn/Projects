                            #### pass generator v2

import tkinter as tk
import ttkbootstrap as tb
from tkinter import ttk

root=tb.Window(themename="darkly")
root.geometry('300x320')
root.resizable(0,0)
root.position_center()
root.title('Pass Generator')

pass_lenght_label=tb.Label(root,text="Lenght of password")
pass_lenght_label.grid(row=0,column=0,pady=5)

nums=[6,8,12,14]



pass_lenght_box=tb.Combobox(root,values=nums)
pass_lenght_box.set(nums[0])
pass_lenght_box.grid(row=1,column=0,pady=5)


pass_gen_label = tb.Label(root, text="Password")
pass_gen_label.grid(row=2, column=0, pady=5) 

pass_box = tk.Entry(root, width=20,bd=0)
pass_box.grid(row=3, column=0,pady=5)


def passgen():
    try:
        import random
        password=''
        pass_lenght=int(pass_lenght_box.get())

        for i in range(pass_lenght):
            password+=chr(random.randint(33,122))
        pass_box.delete(0,'end')    
        pass_box.insert(0,password)
        error=''
        print(len(password))


    except ValueError:
        error=""
        pass_lenght_box.delete(0,'end')
        pass_lenght_box.insert(0,error)
    
    except:
        error="Unexpexted error occurred"
        pass_lenght_box.delete(0,'end')
        pass_box.insert(0,error)

gen_pass_btn=tb.Button(root, text="Generate Pass",command=passgen)
gen_pass_btn.grid(row=4, column=0,pady=5)


def copy():
    content = pass_box.get()
    root.clipboard_clear()  # Clear the clipboard
    root.clipboard_append(content)  # Append the content to clipboard
    root.update()  # Update the clipboard

copy_btn=tb.Button(root,text="Copy",command=copy)
copy_btn.grid(row=5,column=0,pady=5)

root.mainloop()
