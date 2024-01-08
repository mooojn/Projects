                                    ### Version-2

# importing the necesarry modules
import tkinter as tk
import ttkbootstrap as tb
from tkinter import ttk
import os

# Clear the history file
with open("history.txt", "w") as f:
    f.write("")

# gui skeleton
root=tb.Window(themename="darkly")
root.geometry("450x360")
root.resizable(0,0)
root.position_center()
root.title("Calculator")


# input box entered data stored here
expression=''

# input box where all the data is showed
input_box=tk.Text(root,height=2,width=35)
input_box.grid(row=0,column=0,columnspan=4)
input_box.focus()

# button frame where all the buttons are located
buttons=tk.LabelFrame(root)
buttons.grid(row=1, column=0,sticky=tk.W)
op=''
# clear all ('C') button functionality
def del_all():
    global expression,op
    op=''
    input_box.delete(1.0,tk.END)
    expression=''
    input_box.focus()

# clear all ('C') button
clear_all=tb.Button(buttons,text="C",width=6,bootstyle='danger',command=del_all)
clear_all.grid(row=0,column=0,sticky=tk.W,padx=5,pady=5)

# delete one single digit button functionality
def del_one():
    global expression
    current_content = input_box.get("1.0", tk.END)
    if current_content.strip():  # Check if there is any content in the Text widget
        new_content = current_content[:-2]  # Remove the last character and newline
        input_box.delete("1.0", tk.END)  # Clear the current content
        input_box.insert("1.0", new_content)  # Insert the updated content
        expression=expression[:-1]
        input_box.focus()

# delete one single digit button
clear_one=tb.Button(buttons,text='⌫',width=6,bootstyle='danger',command=del_one)
clear_one.grid(row=0,column=2,sticky=tk.W,padx=5,pady=5)


# plus button
plus_btn=tb.Button(buttons,text='+',width=6,bootstyle='warning',command=lambda:action("+"))
plus_btn.grid(row=3,column=3,sticky=tk.W,padx=5,pady=5)

# minus button
minus_btn=tb.Button(buttons,text='-',width=6,bootstyle='warning',command=lambda:action("-"))
minus_btn.grid(row=2,column=3,sticky=tk.W,padx=5,pady=5)

# multiply button
multiply_btn=tb.Button(buttons,text='x',width=6,bootstyle='warning',command=lambda:action("*"))
multiply_btn.grid(row=1,column=3,sticky=tk.W,padx=5,pady=5)

# divide button
divide_btn=tb.Button(buttons,text='÷',width=6,bootstyle='warning',command=lambda:action("/"))
divide_btn.grid(row=0,column=3,sticky=tk.W,padx=5,pady=5)

# power function
def power():
    global op
    op=""
    op='^'
    action("^")

# power button
power_btn=tb.Button(buttons,text='^',width=6,bootstyle='warning',command=power)
power_btn.grid(row=0,column=1,sticky=tk.W,padx=5,pady=5)

previous=''
n1=0
n2=0
res=0

# equal function
def equal():
    global n1,n2,res,op,expression,previous
    expression=input_box.get(1.0,'end')
    try:
        if op=="^":
            previous=expression
            print(previous)
            n1,n2=expression.split('^')
            res=int(n1)**int(n2)
            input_box.delete(1.0,'end')
            input_box.insert(1.0,res)
            expression=str(res)
            op=""
            input_box.focus()
        
    except:
        error="An error occured"
        input_box.delete(1.0,'end')
        input_box.insert(1.0,error)
        expression=''
        op=""
    else:
        try:
            previous=expression
            expression=str(eval(expression))      # eval= evaluate's all of the expression
                                                  # and returns the answer 
            input_box.delete(1.0,'end')                   
            input_box.insert(1.0, expression)
            input_box.focus()
        
            # Save the expression to history
            with open("history.txt", "a") as f:
                f.write(f'{previous.strip()} = {expression.strip()}\n')

        except ZeroDivisionError:
            error="Can't Divide By Zero"
            input_box.delete(1.0,'end')
            input_box.insert(1.0,error)
            expression=''
    
        except:
            error="Unknown Error Occured"    
            input_box.delete(1.0,'end')
            input_box.insert(1.0,error)
            expression=''

# equal button
equal_btn=tb.Button(buttons,text='=',width=6
                    ,bootstyle='success',command=equal)
equal_btn.grid(row=4,column=3,sticky=tk.W,padx=5,pady=5)

# Link Enter key press to the equal button's function
root.bind('<Return>', lambda event: equal())


def prev():
    global previous,expression
    expression=previous
    input_box.delete(1.0,'end')
    input_box.insert("1.0", expression.rstrip("\n"))
    input_box.focus()

prev_btn=tb.Button(buttons,text='Prev',width=6,bootstyle='danger',command=prev)
prev_btn.grid(row=4,column=2,sticky=tk.W,padx=5,pady=5)

# Link "p" key press to the append_p function
root.bind('p', lambda event: prev())
root.bind('P', lambda event: prev())

# button pressed shown on input box
def action(n):
    global expression
    expression=input_box.get(1.0,'end-1c')
    expression+=n
    input_box.delete(1.0,'end')
    input_box.insert(1.0,expression)
    input_box.focus()


# number buttons
num7=ttk.Button(buttons,text='7',width=6,command=lambda: action('7'))
num7.grid(row=1,column=0,sticky=tk.W,padx=5,pady=5)

num8=ttk.Button(buttons,text='8',width=6,command=lambda: action('8'))
num8.grid(row=1,column=1,sticky=tk.W,padx=5,pady=5)

num9=ttk.Button(buttons,text='9',width=6,command=lambda: action('9'))
num9.grid(row=1,column=2,sticky=tk.W,padx=5,pady=5)

num4=ttk.Button(buttons,text='4',width=6,command=lambda: action('4'))
num4.grid(row=2,column=0,sticky=tk.W,padx=5,pady=5)

num5=ttk.Button(buttons,text='5',width=6,command=lambda: action('5'))
num5.grid(row=2,column=1,sticky=tk.W,padx=5,pady=5)

num6=ttk.Button(buttons,text='6',width=6,command=lambda: action('6'))
num6.grid(row=2,column=2,sticky=tk.W,padx=5,pady=5)

num1=ttk.Button(buttons,text='1',width=6,command=lambda: action('1'))
num1.grid(row=3,column=0,sticky=tk.W,padx=5,pady=5)

num2=ttk.Button(buttons,text='2',width=6,command=lambda: action('2'))
num2.grid(row=3,column=1,sticky=tk.W,padx=5,pady=5)

num3=ttk.Button(buttons,text='3',width=6,command=lambda: action('3'))
num3.grid(row=3,column=2,sticky=tk.W,padx=5,pady=5)

num0=ttk.Button(buttons,text='0',width=6,command=lambda: action('0'))
num0.grid(row=4,column=1,sticky=tk.W,padx=5,pady=5)

def history():
    os.startfile("history.txt")
    input_box.focus()

history_btn=tb.Button(buttons,text="History",width=6,bootstyle='info',command=history)
history_btn.grid(row=4,column=0,sticky=tk.W,padx=5,pady=5)

root.mainloop()
