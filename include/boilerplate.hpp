#pragma once

#include <eosio/eosio.hpp>
#include <eosio/multi_index.hpp>
#include <eosio/system.hpp>
#include <eosio/singleton.hpp>
#include <eosio/time.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract("boilerplate")]] boilerplate : public contract {
   public:
      using contract::contract;

      [[eosio::action]]
      void hi( const name user );

      [[eosio::action]]
      void wave( const name user );

      using hi_action = eosio::action_wrapper<"hi"_n, &boilerplate::hi>;
      using wave_action = eosio::action_wrapper<"wave"_n, &boilerplate::wave>;

   private:
      struct [[eosio::table]] config_row {
         name user;
      };

      struct [[eosio::table]] user_row {
         name user;

         uint64_t primary_key() const { return user.value; }
      };

      // Singletons & Multi-indexes
      typedef eosio::singleton<"config"_n, config_row> config_table;
      typedef eosio::multi_index<"user"_n, user_row> user_table;

      // Private helper methods used by other actions.
      void private_hi( name user );
};
