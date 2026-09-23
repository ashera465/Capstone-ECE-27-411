# Capstone-ECE-27-411
This repository holds the active code base for the ECE 27-411 capstone project.


# Git Remote Repository Setup Guide

This guide outlines the steps to connect a local project to a remote Git repository or start fresh with a new one.

## Scenario 1: Connecting an Existing Local Project to a New Remote Repo
Use this workflow if you already have code on your computer and want to push it to a brand-new, empty remote repository.

### 1. Create the Remote Repository
Log into your hosting platform (GitHub, GitLab, Bitbucket) and create a **New Repository**. Give it a name, but leave it empty—do **not** initialize it with a README, `.gitignore`, or license.

### 2. Copy the Remote URL
Copy the provided HTTPS or SSH repository link. It will look something like this:
`https://github.com`

### 3. Initialize and Link Locally
Open your terminal, navigate to your local project folder, and run the following commands:

```bash
# Initialize the local directory as a Git repository
git init

# Stage all files in your project
git add .

# Commit the files with a message
git commit -m "Initial commit"

# Rename your default branch to 'main'
git branch -M main

# Link your local repository to the remote URL (replace the URL below)
git remote add origin <PASTE_REMOTE_URL_HERE>

# Push your code and set the upstream tracking branch
git push -u origin main
```

---

## Scenario 2: Starting Fresh by Cloning an Existing Remote Repo
Use this workflow if the remote repository already exists (or you initialized it on the cloud with a README) and you want to start working on it locally.

### 1. Copy the Remote URL
Copy the HTTPS or SSH link from your cloud repository.

### 2. Clone and Navigate
Open your terminal and run:

```bash
# Clone the repository onto your computer (replace the URL below)
git clone <PASTE_REMOTE_URL_HERE>

# Move into the newly created project folder
cd <repository-name>
```
*Note: Git automatically sets up the remote configuration (`origin`) when you clone.*

---

## Useful Troubleshooting Commands

* **Verify Your Remote Setup:** Check which remote server your local repository is pointing to:
  ```bash
  git remote -v
  ```
* **Change Your Remote URL:** Update the link if you made a typo or switched authentication methods (e.g., from HTTPS to SSH):
  ```bash
  git remote set-url origin <NEW_REMOTE_URL>
  ```
