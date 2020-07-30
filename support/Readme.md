This directory will be used to store various support scripts etc. for development

- `cleanup_all.sh`: **old** script to nuke cmake build files
- `Dockerfile`: docker configuration file for ci/cd environment
    - note: this app doesn't work over xforwarding so docker is only good for running most unit tests atm
- `proj.py`: python[3] interface for ci/cd