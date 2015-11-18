Router.configure({
  layoutTemplate: 'layout',
  loadingTemplate: 'loading',
  notFoundTemplate: 'notFound',
});

Router.route('/landing')

Router.route('/recipes',
{
  name: 'recipeList',
  waitOn: function(){
    return Meteor.subscribe("recipes");
  }
});
Router.route('/ingredients', {
  name: "ingredientList",
  waitOn: function(){
    return Meteor.subscribe("ingredients");
  }
});
Router.route('/historyList');

Router.route('/', {
  name: "shoppingList",
});

var OnBeforeActions = {
    loginRequired: function(pause) {
      if (!Meteor.userId()) {
        this.redirect('landing');
      }
      else{
        this.next();
      }
    },
    alreadyLoggedIn: function(pause) {
      if (Meteor.userId()) {
        this.redirect('shoppingList');
      }
      else{
        this.next();
      }
    }
};

Router.onBeforeAction(OnBeforeActions.loginRequired,{
  except: ["landing"]
});
Router.onBeforeAction(OnBeforeActions.alreadyLoggedIn,{
  only: ["landing"]
});


AccountsTemplates.configureRoute('changePwd');
AccountsTemplates.configureRoute('enrollAccount');
AccountsTemplates.configureRoute('forgotPwd');
AccountsTemplates.configureRoute('resetPwd');
AccountsTemplates.configureRoute('signIn');
AccountsTemplates.configureRoute('signUp');
AccountsTemplates.configureRoute('verifyEmail');
