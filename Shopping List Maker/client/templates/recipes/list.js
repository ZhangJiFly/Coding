Template.recipeList.helpers({
  recipes: function(){
    return Recipes.find();
  }
})
