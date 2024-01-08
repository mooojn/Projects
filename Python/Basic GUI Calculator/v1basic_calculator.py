                                    ### Version-1

# importing the necesarry modules
import tkinter as tk
import ttkbootstrap as tb
from tkinter import ttk
import pdb


# gui skeleton
root=tb.Window(themename="darkly")
root.geometry("400x300")
root.resizable(0,0)
root.position_center()
root.title("Calculator")


# input box entered data stored here
expression=''


# input box where all the data is showed
input_box=tk.Text(root,height=2,width=30)
input_box.grid(row=0,column=0)


# button frame where all the buttons are located
buttons=tk.LabelFrame(root)
buttons.grid(row=1,column=0,sticky=tk.W)

# clear all ('C') button functionality
def del_all():
    global expression
    input_box.delete(1.0,tk.END)
    expression=''

# clear all ('C') button
clear_all=ttk.Button(buttons,text="C",width=6,command=del_all)
clear_all.grid(row=0,column=0,sticky=tk.W)

# delete one single digit button functionality
def del_one():
    global expression
    current_content = input_box.get("1.0", tk.END)
    if current_content.strip():  # Check if there is any content in the Text widget
        new_content = current_content[:-2]  # Remove the last character and newline
        input_box.delete("1.0", tk.END)  # Clear the current content
        input_box.insert("1.0", new_content)  # Insert the updated content
        expression=expression[:-1]

# delete one single digit button
clear_one=ttk.Button(buttons,text='⌫',width=6,command=del_one)
clear_one.grid(row=0,column=2,sticky=tk.W)


# variables for calculations
n1=0
n2=0
result=0
op=''

# plus function
def plus():
    global op
    op='+'
    action('+')

# plus button
plus_btn=ttk.Button(buttons,text='+',width=6,command=plus)
plus_btn.grid(row=3,column=3,sticky=tk.W)

# minus function
def minus():
    global op
    op='-'
    action('-')

# minus button
minus_btn=ttk.Button(buttons,text='-',width=6,command=minus)
minus_btn.grid(row=2,column=3,sticky=tk.W)


# multiply function
def multiply():
    global op
    op='x'
    action('x')

# multiply button
multiply_btn=ttk.Button(buttons,text='x',width=6,command=multiply)
multiply_btn.grid(row=1,column=3,sticky=tk.W)


# divide function
def divide():
    global op
    op='÷'
    action('÷')


# divide button
divide_btn=ttk.Button(buttons,text='÷',width=6,command=divide)
divide_btn.grid(row=0,column=3,sticky=tk.W)


# power function
def power():
    global op
    op='^'
    action('^')

# power button
power_btn=ttk.Button(buttons,text='^',width=6,command=power)
power_btn.grid(row=4,column=2,sticky=tk.W)

# percentage function
def percentage():
    global op
    op='%'
    action('%')

# percentage button
percentage_btn=ttk.Button(buttons,text='%',width=6,command=percentage)
percentage_btn.grid(row=0,column=1,sticky=tk.W)


# equal function
def equal():
    global expression,op,n1,n2,result
    n1,n2=expression.split(op)    
    
    if   op == "+":                 # addition calculation
        result=int(n1)+int(n2)
    elif op == "-":                 # subtraction calculation
        result=int(n1)-int(n2)
    elif op == "x":                 # multiply calculation
        result=int(n1)*int(n2)
    elif op == "÷":                 # divide calculation
        result=int(n1)//int(n2)
    elif op == '%':                 # percentage calculation
        result=(int(n1)/100)*int(n2)
    elif op == '^':                 # power calculation
        result=int(n1)**int(n2)

    input_box.delete(1.0,tk.END)
    input_box.insert(1.0, result)
    expression=str(result)

# equal button
equal_btn=ttk.Button(buttons,text='=',width=6,command=equal)
equal_btn.grid(row=4,column=3,sticky=tk.W)

# button pressed shown on input box
def action(n):
    global expression
    expression+=str(n)
    input_box.delete(1.0,'end')
    input_box.insert(1.0,expression)


# number buttons
num7=ttk.Button(buttons,text='7',width=6,command=lambda: action(7))
num7.grid(row=1,column=0,sticky=tk.W)

num8=ttk.Button(buttons,text='8',width=6,command=lambda: action(8))
num8.grid(row=1,column=1,sticky=tk.W)

num9=ttk.Button(buttons,text='9',width=6,command=lambda: action(9))
num9.grid(row=1,column=2,sticky=tk.W)

num4=ttk.Button(buttons,text='4',width=6,command=lambda: action(4))
num4.grid(row=2,column=0,sticky=tk.W)

num5=ttk.Button(buttons,text='5',width=6,command=lambda: action(5))
num5.grid(row=2,column=1,sticky=tk.W)

num6=ttk.Button(buttons,text='6',width=6,command=lambda: action(6))
num6.grid(row=2,column=2,sticky=tk.W)

num1=ttk.Button(buttons,text='1',width=6,command=lambda: action(1))
num1.grid(row=3,column=0,sticky=tk.W)

num2=ttk.Button(buttons,text='2',width=6,command=lambda: action(2))
num2.grid(row=3,column=1,sticky=tk.W)

num3=ttk.Button(buttons,text='3',width=6,command=lambda: action(3))
num3.grid(row=3,column=2,sticky=tk.W)

num0=ttk.Button(buttons,text='0',width=6,command=lambda: action(0))
num0.grid(row=4,column=1,sticky=tk.W)

doublezero_btn=ttk.Button(buttons,text="00",width=6,command=lambda: action("00"))
doublezero_btn.grid(row=4,column=0)


root.mainloop()
