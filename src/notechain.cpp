#include <notechain.hpp>

void notechain::update( name user, std::string& note ) {
   // to sign the action with the given account
   require_auth( user );

   // create new / update note depends whether the user account exist or not
   if (isnewuser(user)) {
      // insert new note
      _notes.emplace( _self, [&]( auto& new_user ) {
         new_user.prim_key    = _notes.available_primary_key();
         new_user.user        = user;
         new_user.note        = note;
         new_user.timestamp   = eosio::current_block_time();
      });
   } else {
      // get object by secordary key
      auto note_index = _notes.get_index<name("getbyuser")>();
      auto &note_entry = note_index.get(user.value);
      // update existing note
      _notes.modify( note_entry, _self, [&]( auto& modified_user ) {
         modified_user.note      = note;
         modified_user.timestamp = eosio::current_block_time();
      });
   }
}

bool notechain::isnewuser( name user ) {
   // get notes by using secordary key
   auto note_index = _notes.get_index<name("getbyuser")>();
   auto note_iterator = note_index.find(user.value);

   return note_iterator == note_index.end();
}
