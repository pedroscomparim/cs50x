from cs50 import get_string

letters_count = words_count = sentences_count = 0

text = get_string("Text: ")

for char in text:
    if char.isalpha():
        letters_count += 1
    elif char == " ":
        words_count += 1
    elif char in ".!?":
        sentences_count += 1

# Calculate the average number of letters and sentences per 100 words
words_count += 1

L = 100 * letters_count / words_count
S = 100 * sentences_count / words_count

# Round the grade level to the nearest integer
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")
