Players = new Mongo.Collection('players');

Meteor.methods({
  playerInsert: function() {
  
    var user = Meteor.user();
    var player = {
      userId: user._id, 
      username: user.username, 
      submitted: new Date(),
    };
    
    var playerId = Players.insert(player);
    
    return {
      _id: playerId
    };
  },
});