# Capstone-ECE-27-411
This repository holds the active code base for the ECE 27-411 capstone project.


# Git Remote Repository Setup Guide

This guide outlines the steps to connect to this repo.

### 1. Clone the current Repository 
```bash
# Clone the repository onto your computer
git clone https://github.com/ashera465/Capstone-ECE-27-411

# Move into the newly created project folder
cd Capstone-ECE-27-411/
```
**Note: Git automatically sets up the remote configuration (`origin`) when you clone.**

*So whenever you use 'origin' its a alias for "github.com/ashera465/Capstone-ECE-27-411/"*

**It will also ask for a PAT, or a GitHub login interface may show up.**

*You can find tutorials on how to set authentication up*

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
Once the upstream tracking branch is set, in further pushes you only need to run
```bash
git push 
```
---

## Useful Troubleshooting Commands

* **Verify Your Remote Setup:** Check which remote server your local repository is pointing to:
  ```bash
  git remote -v
  ```
* **Verify Branches in Local Git Repo:** Check which branches are being tracked by git:
  Git highlights in green which branch you're working in.
  There should be at least:
  * `main` <-- Working branch
  * `remotes/origin/main` <-- Remote tracking branch
  ```bash
  git branch -a
  ```
