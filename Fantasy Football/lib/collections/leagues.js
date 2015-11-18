Leagues = new Mongo.Collection('leagues');

Meteor.methods({
  leagueInsert: function(name) {
  
    var user = Meteor.user();
    var league = {
      userId: user._id, 
      username: user.username,
      leagueName: name,
      submitted: new Date(),
    };
    
    var leagueId = Leagues.insert(league);
    
    return {
      _id: leagueId
    };
  },
});