package main

/*
	Conceptual Example:
	Let’s try to understand the Composite pattern with an example of an operating system’s
	file system. In the file system, there are two types of objects: files and folders.
	There are cases when files and folders should be treated to be the same way. This is
	where the Composite pattern comes in handy.

	Imagine that you need to run a search for a particular keyword in your file system.
	This search operation applies to both files and folders. For a file, it will just look
	into the contents of the file; for a folder, it will go through all files of that
	folder to find that keyword.
*/

func main() {
    file1 := &File{name: "File1"}
    file2 := &File{name: "File2"}
    file3 := &File{name: "File3"}

    folder1 := &Folder{
        name: "Folder1",
    }

    folder1.add(file1)

    folder2 := &Folder{
        name: "Folder2",
    }
    folder2.add(file2)
    folder2.add(file3)
    folder2.add(folder1)

    folder2.search("rose")
}
