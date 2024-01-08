import tkinter as tk
import ttkbootstrap as tb
import random
import webbrowser

# Create the main window using ttkbootstrap theme
root = tb.Window(themename="darkly")
root.geometry('500x500')  # Set window size
root.resizable(0, 0)  # Disable window resizing
root.position_center()  # Position the window at the center of the screen
root.title("Word Guess Game")  # Set the window title

## variables
win = False  # Indicates whether the game has been won
hint_used = 0  # Flag to track if a hint has been used
guess_count = 0  # Count of attempts to guess the word
user_guess = ''  # User's current guess

# List of words to guess
words =[
    'ant', 'acid', 'apple', 
    'bear', 'ball', 'banana',
    'crab', 'cake', 'cherry',
    'deer', 'doll', 'date'
]
guess_word = random.choice(words)  # Randomly select a word from the list
print(guess_word)
# Widgets setup
user_guess_label = tb.Label(text="Guess the word : ")
user_guess_label.grid(row=0, column=0, padx=5, pady=5)

user_guess_entry = tb.Entry(root)
user_guess_entry.grid(row=0, column=1, padx=5, pady=10)
user_guess_entry.focus()  # Set focus on the user input entry field

try_label = tb.Label(text='')  # Label for displaying feedback on each guess
hint_label = tb.Label(text="")  # Label for hint-related messages
hint_btn_no = tb.Button(text="")  # Button for declining a hint
hint_btn_yes = tb.Button(text="")  # Button for accepting a hint

def open_url():
    # Open a URL in the default web browser
    url = "https://deanmorriscards.co.uk/products/you-are-very-very-gay-card-2305"
    webbrowser.open(url)

def show_hint():
    global hint_used
    hint_used = 1
    user_guess_entry.delete(0, 'end')
    user_guess_entry.insert(0, guess_word[0])  # Provide a hint by filling in the first letter of the word
    hide_hint()

def hide_hint():
    hint_label.config(text="")
    user_guess_entry.focus()
    hint_btn_no.config(text='', width=0)
    hint_btn_no.grid_forget()
    hint_btn_yes.config(text='', width=0)
    hint_btn_yes.grid_forget()

def guess():
    global user_guess, guess_word, guess_count, win, hint_used
    while True:
        user_guess = user_guess_entry.get()
        if win == False:
            if user_guess == guess_word:
                guess_count += 1
                win = True
                try_label.config(text='')
                hint_label.config(text="")
                win_label = tb.Label(text=f"Congratulations\nYou WON!!!\nYou took {guess_count} try")
                win_label.grid(row=2, columnspan=2)
                win_btn = tb.Button(width=12, text="Click here for\nREWARD",bootstyle='success', command=open_url)
                win_btn.grid(row=3, columnspan=2, padx=10, pady=10)
            else:
                user_guess_entry.delete(0, 'end')
                if hint_used == 1:
                    user_guess_entry.insert(0, guess_word[0])  # If hint used, fill in the first letter of the word
                guess_count += 1
                user_guess_entry.focus()
                try_label.config(text=f'"{user_guess}" is not the correct\nword please\nTry Again')
                try_label.grid(row=2, columnspan=2)
                if guess_count == 2:
                    hint_label.config(text="\nDo you want a hint")
                    hint_label.grid(row=4, columnspan=2)
                    hint_btn_yes.config(text="Yes",bootstyle="info", command=show_hint)
                    hint_btn_no.config(text="No",bootstyle="danger", command=hide_hint)
                    hint_btn_yes.grid(row=5, column=0, padx=10, pady=10)
                    hint_btn_no.grid(row=5, column=1, padx=10, pady=10)
                    break
                break
        else:
            user_guess_entry.config(command=None)  # Disable further input if the game is won
            break

# Submit button for guessing
user_guess_submit_btn = tb.Button(width=6, text="Submit", command=guess)
user_guess_submit_btn.grid(row=1, columnspan=2, sticky=tk.E, padx=5, pady=5)

# Start the main event loop to run the GUI
root.mainloop()
