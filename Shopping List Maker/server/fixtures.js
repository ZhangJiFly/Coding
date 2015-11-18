var mealList = [
  {name: "Spagetti Bolg", method:"", ingredients: [{name: "Mince", quantity: 400, quantityUnit: "g"}, {name: "Peppers", quantity:1}, {name:"Onions", quantity: 1}, {name:"Spagetti", quantity:100, quantityUnit: "g"}, {name:"Vegetables", quantity:300, quantityUnit: "g"}], recipes:["Ragu"]},
  {name: "Shepherds Pie", method:"", ingredients: [{name:"Mince", quantity: 400, quantityUnit: "g"}, {name:"Onions", quantity: 1}, {name:"Beef Stock", quantity: 2, quantityUnit: "cubes"}], recipes: ["Mash"]},
  {name: "Mash", method:"", ingredients: [{name:"Milk", quanity: 150, quantityUnit: "g"}, {name:"Potatoes", quanity:200, quantityUnit: "g"}, {name:"Butter", quantity: 30, quantityUnit: "g"}], recipes: []},
  {name: "Ragu", method:"", ingredients: [{name:"Tinned Tomatoes", quanity: 1, quantityUnit: "Tins"}, {name:"Basil", quantity: 20, quantityUnit: "g"}, {name:"Garlic", quantity: 2, quantityUnit: "cloves"}], recipes: []},
];

if(Meteor.users.findOne({username: "jmarks"}) === null || Meteor.users.findOne({username: "jmarks"}) === undefined){
  Accounts.createUser({
    'username'  : 'jmarks',
    'email'     : 'john@doe.com',
    'password'  : 'password' //encrypted automatically
  });
}


var jmarks = Meteor.users.findOne({username: "jmarks"});

if(Recipes.find().count() === 0){
  mealList.forEach(function(recipe){
    Recipes.insert(_.extend(recipe, {userId: jmarks._id}));
  });
}

mealList.forEach(function(recipe){
  recipe.ingredients.forEach(function(ingredient){
    if(Ingredients.find({name: ingredient.name}).count() === 0)
    Ingredients.insert({name: ingredient.name, userId: jmarks._id})
  })
})

// {name: "Mac and Cheese", method:"", ingredients: ["Macaroni", "Bacon", "Onions"], recipes: ["Cheese Sauce"]},
// {name: "Manuals Meal", method:"", ingredients: ["Bacon", "Salsa", "Fajita Sauce", "Wraps", "Mince", "Peppers", "Onions"], recipes: ["Cheese Sauce"]},
// {name: "Thai Red Curry", method:"", ingredients: ["Chicken/Prawns/Beef", "Soy Sauce", "Fish Sauce", "Coconut Milk", "Vegetables"] recipes: ["Curry Paste"]},
// {name: "Aubergine Pizza", method:"", ingredients: ["Aubergine", "Mozorella", "Toppings"] recipes: ["Ragu"]},
// {name: "Real Pizza", method:"", ingredients: ["Chedder", "Mozorella", "Toppings"], recipes: ["Ragu, Dough"]},
// {name: "Lasagna", method:"", ingredients: ["Bacon", "Tomato Sauce", "Lasagne", "Mince", "Peppers", "Onions"], recipes: ["Cheese Sauce", "Ragu"]},
// {name: "Fajitas", method:"", ingredients: ["Chicken", "Fajita Sauce", "Wraps", "Peppers", "Onions"], recipes: []},
// {name: "Risotto", method:"", ingredients: ["Risotto Rice", "Vegetable Stock", "Peas", "Onion", "Peppers", "Chicken"], recipes: []},
// {name: "Pesto Pasta", method:"", ingredients: ["Chicken", "Broccoli", "Pasta", "Courgette"], recipes: ["Pesto"]},
// {name: "Burgers", method:"", ingredients: ["Mince", "Buns", "Bacon", "Cheese"], recipes: []},
// {name: "Satay", method:"", ingredients: ["Ginger", "Peanut Butter", "Garlic", "Chicken", "Soy Sauce", "Seasame Oil"], recipes: []},
// {name: "Mince Pasta Bake", method:"", ingredients: ["Macaroni/Penne", "Sauce", "Meat"], recipes: ["Cheese Sauce"]},
// {name: "Peanut Noodles", method:"", ingredients: ["Ginger", "Peanut Butter", "Garlic", "Soy Sauce", "Seasame Oil", "Peppers", "Hot Sauce"], recipes: []},
// {name: "Spagetti Carbonara", method:"", ingredients: ["Spagetti", "Bacon", "Garlic Oil", "Eggs", "Hard Cheese", "White Wine"], recipes: []},
// {name: "Chicken Broccoli pie", method:"", ingredients: ["Broccoli", "Chicken"], recipes: ["Pastry", "Cheese Sauce"]},
// {name: "Steak & Ale Pie", method:"", ingredients: ["Beef Stock/Gravy", "Steak", "Ale"], recipes: ["Pasty"]},
// {name: "Stir Fry", method:"", ingredients: ["Stir Fry Sauce", "Noodles", "Meat", "Peppers", "Onions/Spring Onions", "Soy Sauce", "Oil"], recipes: []},
// {name: "Tuna & Puttanesca Pasta", method:"", ingredients: ["Tuna", "Puttanesca", "Pasta"], recipes: []},
// {name: "Chilli", method:"", ingredients: ["Mince", "Peppers", "Onions", "Sauce", "Rice", "Vegetables", "Chilli Beans"], recipes: []},
// {name: "White Trash Ham", method:"", ingredients: ["Coke", "Leg of Ham"], recipes: ["Mash"]},
// {name: "Easy Meal", method:"", ingredients: ["Bought Pizza", "Filled Pasta", "Oven Food"], recipes: []},
// {name: "Cheese Sauce", method:"", ingredients: ["Chedder", "Gruyere", "Hard Cheese", "Mozorella", "Milk", "Butter"], recipes: []},
// {name: "Mash", method:"", ingredients: ["Milk", "Potatoes", "Butter"], recipes: []},
// {name: "Pastry", method:"", ingredients: ["Flour", "Trex/Veg Fat", "Butter", "Eggs"], recipes: []},
// {name: "Pesto", method:"", ingredients: ["Garlic", "Basil", "Pine Nuts", "Hard Cheese", "Extra Virgin Oil", "Lemon Juice"], recipes: []},
