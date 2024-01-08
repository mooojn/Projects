import os
import tkinter as tk
from tkinter import ttk
from csv import DictWriter
win=tk.Tk()
win.title("moon")               # Application name

# Labels
name_label=ttk.Label(win,text="Enter your name : ",)
name_label.grid(row=0,column=0,sticky=tk.W)

age_label=ttk.Label(win,text="Enter your age : ",)
age_label.grid(row=1,column=0,sticky=tk.W)

email_label=ttk.Label(win,text="Enter your Email : ")
email_label.grid(row=2,column=0,sticky=tk.W)

gender_label=ttk.Label(win,text="Select your gender : ")
gender_label.grid(row=3,column=0)   
# Entry Boxes
name_var=tk.StringVar()
name_entrybox=ttk.Entry(win,width=16,textvariable=name_var)
name_entrybox.grid(row=0,column=1)
name_entrybox.focus()

age_var=tk.IntVar()
age_entrybox=ttk.Entry(win,width=16,textvariable=age_var)
age_entrybox.grid(row=1,column=1)

email_var=tk.StringVar()
email_entrybox=ttk.Entry(win,width=16,textvariable=email_var)
email_entrybox.grid(row=2,column=1)

gender_var=tk.StringVar()

# Combo Box
gender_combobox=ttk.Combobox(win,width=13,textvariable=gender_var,state='readonly')
gender_combobox['values']=('Male',"Female","Other")
gender_combobox.current(0)
gender_combobox.grid(row=3,column=1)      # Position of 'gender' button  

# Radio Button
relation=tk.StringVar()

relation_type=ttk.Radiobutton(win,text='Single',value='Single',variable=relation)
relation_type.grid(row=4,column=0)        # Position of 'single' button

relation_type=ttk.Radiobutton(win,text='Married',value='Married',variable=relation)
relation_type.grid(row=4,column=1)        # Position of 'married' button

relation.set('Single')                    # Default value assigned 'Single'

# Check Button
subscribe_var=tk.IntVar()
subscribe=ttk.Checkbutton(win,text="Do you want to subscribe?",variable=subscribe_var)
subscribe.grid(row=5,columnspan=3)    

# Defining what happens when Submit button is clicked
def action():                                       
    user_name=name_var.get()        # Getting the values        
    user_age=age_var.get()          # From the gui interface                  
    user_email=email_var.get()
    user_gender=gender_var.get()
    user_relation=relation.get()

    if subscribe_var.get() == 1:    # Checking if subsribed
        subscribed="Yes"
    else:
        subscribed='No'
    
    with open('data.csv','a',newline='') as f:  # Writing data into file    
        
        dataW=DictWriter(f,fieldnames=['Name',"Age","Email","Gender",
                                       "Relationship","Subscribed"])
       
        if os.stat('data.csv').st_size == 0:    # Headers check if written
            dataW.writeheader()
        
        dataW.writerow({                        # Data assigning  
            'Name' : user_name,
            'Age' : user_age,
            'Email': user_email,
            'Gender':user_gender,
            "Relationship":user_relation,
            "Subscribed":subscribed
        })             
    
    name_entrybox.delete(0,tk.END)   #  Reset values 
    age_entrybox.delete(0,tk.END)    #              When Submit 
    email_entrybox.delete(0,tk.END)  #                         Is clicked
                                    
                                    
    ## win.destroy()                 # Closes program when Submit is clicked

# Submit Button
submit_button=ttk.Button(win,text="Submit",command=action)
submit_button.grid(row=6,column=2)   # Position of submit button


win.mainloop()                       # Without this program would'nt load
       