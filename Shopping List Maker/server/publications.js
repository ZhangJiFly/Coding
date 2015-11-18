Meteor.publish('ingredients', function() {
  return Ingredients.find({userId: this.userId});
});

Meteor.publish('recipes', function() {
  return Recipes.find({userId: this.userId});
});
