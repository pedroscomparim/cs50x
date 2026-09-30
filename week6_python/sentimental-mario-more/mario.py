from cs50 import get_int

# Prompt the user for a valid height between 1 and 8
while True:
    height = get_int("Height: ")
    if 1 <= height <= 8:
        break

# Print each row with leading spaces, hashes, and the two-space gap
for i in range(1, height + 1):
    print((height - i) * " " + i * "#" + "  " + i * "#")
