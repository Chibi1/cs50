# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

### The longest word in the dictionary supplied

## According to its man page, what does `getrusage` do?

### Used to examine the resource usage of a process

## Per that same man page, how many members are in a variable of type `struct rusage`?

## 16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

### Easier to follow syntactically

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

### The loop will loop through every character in the file.
### If the letter is alphabetical or an '\'', then the letter is appended to the word array.
### If the resulting index is a larger than 45 (length of the largest word), the word is disregarded.
### Otherwise, the word if accepted.
### If the word contains digits, it will also be subsequently disregarded.
### Once we have found a word, the char array is terminated with a '\0'.
### The word counter is updated.
### The spelling is checked using the `check` function and the step is timed.
### If the word is misspelt (not found in dictionary), then it is printed and the misspellings counter is incremented by one.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

### `fget` is able to handle with correct implementation strings that contain numbers and non-alphabetic characters.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

### do that no words or dictionary items can be changed by code once loaded for indexing.
