import random

## variables
hint=''
hint_used=0
guess_count=0
actual_user_guess=''

# words to guess
words=['cat','dog','owl','ant','fly']
guess_word=random.choice(words)
print(guess_word)

user_guess=input("What is the word  : ")
guess_count+=1
actual_user_guess=user_guess

while True:
    if actual_user_guess==guess_word:
        print("You WON!!")
        print(f"You took {guess_count} tries")
        break
    else:
        if guess_count==2:
            hint=guess_word[0]
            user_guess=input(f"Enter word Starting with {hint}")
            guess_count+=1
            actual_user_guess=hint+user_guess
            hint_used=1
        elif hint_used==1:
            user_guess=input(f"Enter word Starting with {hint}")
            guess_count+=1
            actual_user_guess=hint+user_guess
        else:
            user_guess=input("Try another : ")    
            guess_count+=1
