                            #### pass generator v1


import tkinter as tk
import ttkbootstrap as tb
from tkinter import ttk


root=tb.Window(themename="darkly")
root.geometry('300x300')
# root.resizable(0,0)
root.position_center()
root.title('Pass Generator')

label = tb.Label(root, text="Pass below")
label.grid(row=0, column=0, columnspan=2)  # Adjusted columnspan

text = tk.Text(root, width=20,height=2)
text.grid(row=1, column=0, rowspan=1)  # Adjusted columnspan


def pasg():
     ### password generator
     import random

     chars="abcdefghijklmnopqrstuvwxyzABCDEFGHIOJKLMNOPQRSTUVWXYZ123456789"
     symbols="!@#$%^&*_"

     ## password v1

     # shuffling the symbols
     symbols_list=list(symbols)
     random.shuffle(symbols_list)
     shuffled_symbols=''.join(symbols_list)
     # print(shuffled_symbols)

     # shuffling the characters
     chars_list=list(chars)
     random.shuffle(chars_list)
     shuffled_chars=''.join(chars_list)
     password1=shuffled_chars[0:9]                 # storing the first 8 letters of
                                                 # the shuffled characters          

     # adding "2" symbols in the pass
     for i in range(2):
         j=random.choice(shuffled_symbols)    
         if j not in password1:
             password1+=j
         else:
             j=random.choice(shuffled_symbols)
             password1+=j

     # print(f'\nPassword : {password1}')          # symbols at last
     # print(len(password1))                       

     ## password v2
     password1_list=list(password1)                # symbols shuffled
     random.shuffle(password1_list)
     password2="".join(password1_list)

     text.delete(1.0,'end')
     text.insert(1.0,password2)
     # print(f'\nPassword : {password2}')
     # print(len(password2))

    
button=tb.Button(root, text="Generate Pass",command=pasg)
button.grid(row=2, column=0,pady=5)  # Adjusted columnspan

def copy():
    content = text.get("1.0", tk.END)
    root.clipboard_clear()  # Clear the clipboard
    root.clipboard_append(content)  # Append the content to clipboard
    root.update()  # Update the clipboard


copy_btn=tb.Button(root,text="Copy",command=copy)
copy_btn.grid(row=3,column=0,pady=5)

root.mainloop()
