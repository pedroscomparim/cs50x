from cs50 import get_string

# Prompt the user for a credit card number
card_number = get_string("Number: ")

# Calculate the checksum
position = 0
checksum = 0

for i in range(len(card_number) - 1, -1, -1):
    digit = int(card_number[i])

    # Multiply every other digit by 2
    if position % 2 == 1:
        digit *= 2
        checksum += sum(int(d) for d in str(digit))
    else:
        checksum += digit

    position += 1

# Get the first one and two digits
first_digit = int(card_number[0])
first_two_digits = int(card_number[:2])

# Check the checksum and identify the card type
if checksum % 10 != 0:
    print("INVALID")
elif len(card_number) == 15 and (first_two_digits == 34 or first_two_digits == 37):
    print("AMEX")
elif len(card_number) == 16 and 51 <= first_two_digits <= 55:
    print("MASTERCARD")
elif len(card_number) in (13, 16) and first_digit == 4:
    print("VISA")
else:
    print("INVALID")
