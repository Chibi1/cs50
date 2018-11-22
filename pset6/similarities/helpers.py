from nltk.tokenize import sent_tokenize

def lines(a, b):
    """Return lines in both a and b"""

    file1 = a
    file2 = b

    # store each line of file in list
    lines1 = file1.splitlines()
    lines2 = file2.splitlines()

    inBoth = []

    # if row in both files, append to new array
    for i, line in enumerate(lines1):
        if (lines1[i] not in inBoth) and (lines1[i] != ""):
            if (lines1[i] in lines2):
                inBoth.append(line)

    return inBoth


def sentences(a, b):
    """Return sentences in both a and b"""

    file1 = a
    file2 = b

    # store each sentence of file in list
    lines1 = sent_tokenize(file1)
    lines2 = sent_tokenize(file2)

    inBoth = []

    # if sentence in both files, append to new array
    for i, line in enumerate(lines1):
        if lines1[i] not in inBoth:
            if (lines1[i] in lines2):# and (lines1[i] not in lines1):
                inBoth.append(line)

    return inBoth


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    file1 = a
    file2 = b

    # store each substring of file in list
    lines1 = []
    lines2 = []

    for i, v in enumerate(file1):
        if len(file1[i:i+n]) == n:
            lines1.append(file1[i:i+n])

    for i, v in enumerate(file2):
        if len(file2[i:i+n]) == n:
            lines2.append(file2[i:i+n])

    inBoth = []

    # if substring in both files, append to new array
    for i, line in enumerate(lines1):
        if lines1[i] not in inBoth:
            if (lines1[i] in lines2):# and (lines1[i] not in lines1):
                inBoth.append(line)

    return inBoth
