# EOSIO Smart Contract Boilerplate

## Build

```
./build.sh
```

## Smart Contract Name: `notechain`
### Table struct:

- notestruct: multi index table to store the notes
  - prim_key(uint64): primary key
  - user(name): account name for the user
  - note(string): the note message
  - timestamp(uint64): the store the last update block time

### Public method:

- isnewuser => to check if the given account name has note in table or not

### Public actions:

- update => put the note into the multi-index table and sign by the given account

> Note: Replace the contract class name when you start your own project