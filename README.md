# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The longest possible properly spelled word.

## According to its man page, what does `getrusage` do?

"Get resource usage." It returns the usage statistics for a given thread or group of threads.

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

We want to know the difference in usage for every function, and it's that difference that tells us our runtimes.

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The `for` loop uses the `fgetc` function to read through each word in the text, declaring them as the variable `c` each time. If instead of reaching a word, it hits `EOF`, it will stop reading. Otherwise `fgetc` must continue to run.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

You can easily receive a stack overflow with `fscanf` with the large texts files we will be using.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

We don't want them to be modified because we will be using them often.# speller
