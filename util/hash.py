import string
def hash(word):
    l = []
    k = 3
    for c in word:
        l.append(chr((ord(c) ^ k) % 95 + 33))
        k = k * (k - 1) + ord(c)
    return "".join(l)

hashed_pass = "2-X/Eg/Eh"
alpha = string.ascii_letters + string.digits
pw = []
for i in range(1, len(hashed_pass) + 1):
    for c in alpha:
        pw.append(c)
        if hashed_pass[:i] == hash("".join(pw)):
            break
        else:
            pw.pop()

print("".join(pw))
