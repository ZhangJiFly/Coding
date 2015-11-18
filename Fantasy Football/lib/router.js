Router.configure({
  layoutTemplate: 'layout',
  loadingTemplate: 'loading',
  notFoundTemplate: 'notFound',
  waitOn: function() {
    return []
  }
});

Router.route('/games');
Router.route('/leagues');
Router.route('/friends');
Router.route('/players');
Router.route('/aboutUs');

Router.route('/', {
  name: 'home',
});

var requireLogin = function() {
  if (! Meteor.user()) {
    if (Meteor.loggingIn()) {
      this.render(this.loadingTemplate);
    } else {
      this.render('accessDenied');
    }
  } else {
    this.next();
  }
}
