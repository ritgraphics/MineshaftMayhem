## Cloning the Repo
```
git clone --recursive https://github.com/ritgraphics/Game
```
or
```
git clone --recursive https://github.com/ritgraphics/Game
cd VixenEngine
git submodule init
git submodule update
```

## Updating the Vixen Submodule
```
cd VixenEngine
git checkout master
```

## General Repository Guidelines
* [Don't be a butthole](CODE_OF_CONDUCT.md)
* Do not push to master. Ever.
* Provide descriptive commit messages. A single line commit is rarely enough detail.
* File issues compulsively.

## Committing to `dev`
```
git commit -am "...message..."
git pull --rebase
git push origin dev
```

## Creating and Merging Feature Branch
```
git checkout -b feature-*                     # feature branch names should be descriptive, 
                                              # start with the word feature, and separate words with dashes
git commit -am "...message..."
git pull --rebase
git push origin feature-*                     # where feature-* is your feature branch name
                                              # Repeat ad nauseam until feature is complete
```
When feature is complete, perform a [Pull Request](https://github.com/ritgraphics/Game/pulls) ([info here](https://help.github.com/articles/using-pull-requests/)).

## Git Commit Messages

* Use the present tense ("Add feature" not "Added feature")
* Use the imperative mood ("Move cursor to..." not "Moves cursor to...")
* Limit the first line to 72 characters or less
* Reference issues and pull requests liberally
* If your code doesn't build, reconsider committing

