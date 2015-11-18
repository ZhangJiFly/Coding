Router.configure({
  layoutTemplate: 'layout',
  loadingTemplate: 'loading',
  notFoundTemplate: 'notFound',
  waitOn: function() { 
    return [Meteor.subscribe('notifications'), Meteor.subscribe('top-5-posts')]
  }
});

PostsListController = RouteController.extend({
  template: 'postsList',
  action: function(){
    EasySearch.changeProperty('posts', 'filter', this.filter);
    var instance = EasySearch.getComponentInstance({index: 'posts', id: 'search'})
    instance.triggerSearch();
    this.render();
  },
});

HomeController = PostsListController.extend({
  filter: {}
});

PodcastPostsController = PostsListController.extend({
  filter: {category: "Podcast"}
});


ReviewPostsController = PostsListController.extend({
  filter: {category: "Reviews"}
});

AuthorPostsController = PostsListController.extend({
  onBeforeAction: function(){
    this.filter = {author: this.params.author};
    this.next();
  }
});

Router.route('/posts/:_id', {
  name: 'postPage',
  waitOn: function() {
   return [
   Meteor.subscribe('singlePost', this.params._id),
   Meteor.subscribe('comments', this.params._id)
   ];
 },
 data: function() { return Posts.findOne(this.params._id); }
});

Router.route('/submit', {name: 'postSubmit'});
Router.route('/aboutUs', {fastRender: true});
Router.route('/podcast/:postsLimit?', {name: 'podcastPosts', controller: PodcastPostsController});
Router.route('/review/:postsLimit?', {name: 'reviewPosts', controller: ReviewPostsController}, function(){
  var id = this.params._id;
});
Router.route('/author/:author/:postsLimit?', {name: 'authorPosts', controller: AuthorPostsController});
Router.route('/:postsLimit?', {
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

Router.onBeforeAction('dataNotFound', {only: 'postPage'});
Router.onBeforeAction(requireLogin, {only: 'postSubmit'});
