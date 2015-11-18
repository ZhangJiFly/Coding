Meteor.publish('comments', function(postId) {
  check(postId, String);
  return Comments.find({postId: postId});
});

Meteor.publish('top-5-posts', function(){
  return Posts.find({}, {sort: {submitted: -1}, limit: 5});
})

Meteor.publish('notifications', function() {
  return Notifications.find({userId: this.userId, read: false});
});

Meteor.publish('singlePost', function(id) {
  check(id, String)
  return Posts.find(id);
});