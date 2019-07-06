#pragma once

#include <eosio/eosio.hpp>
#include <eosio/system.hpp>

using namespace eosio;

class [[eosio::contract("notechain")]] notechain : public contract {
   public:
      using contract::contract;

      // constructor
      notechain( name receiver, name code, datastream<const char*> ds ):
                  contract( receiver, code, ds ),
                  _notes( receiver, receiver.value ) {}

      [[eosio::action]]
      void update( name user, std::string& note );

      using update_action = eosio::action_wrapper<"update"_n, &notechain::update>;

   private:
      struct [[eosio::table]] notestruct {
         uint64_t         prim_key;  // primary key
         name             user;      // account name for the user
         std::string      note;      // the note message
         block_timestamp  timestamp; // the store the last update block time

         // primary key
         auto primary_key() const { return prim_key; }
         // secondary key
         // only supports uint64_t, uint128_t, uint256_t, double or long double
         uint64_t get_by_user() const { return user.value; }
      };

      // create a multi-index table and support secondary key
      typedef eosio::multi_index< name("notestruct"), notestruct,
         indexed_by< name("getbyuser"), const_mem_fun<notestruct, uint64_t, &notestruct::get_by_user> >
      > note_table;

      note_table _notes;

      // Private helper methods used by other actions.
      bool isnewuser( name user );
};
