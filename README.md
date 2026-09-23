# Capstone-ECE-27-411
This repository holds the active code base for the ECE 27-411 capstone project.


# Git Remote Repository Setup Guide

This guide outlines the steps to connect to this repo.

### 1. Clone the current Repository 
```bash
# Clone the repository onto your computer
git clone https://github.com/ashera465/Capstone-ECE-27-411

# Move into the newly created project folder
cd <repository-name>
```
*Note: Git automatically sets up the remote configuration (`origin`) when you clone.*
*It will also ask for PAT authentication token since only collaborators can interact with this repo*
*You can find tutorials on how to get those if you don't have one already*
---

At this point a local git repo is made, and it is linked to this remote repo.

### 2. Making commits

Firstly, make sure that if you're working on something do it inside a folder that only you're interacting with.
Otherwise we have to deal with merge conflicts.

Anyway, open the terminal, navigate to the local project folder (of the cloned repo), and run the following commands:

```bash
# Stage all files in your project
git add .

# Commit the files with a message
git commit -m "<Message describing the commit>"

# Push your code and set the upstream tracking branch
git push -u origin main
```

---

## Useful Troubleshooting Commands

* **Verify Your Remote Setup:** Check which remote server your local repository is pointing to:
  ```bash
  git remote -v
  ```
