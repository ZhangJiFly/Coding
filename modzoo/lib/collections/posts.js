Posts = new Mongo.Collection('posts');

Posts.initEasySearch(['author', 'content', 'title', 'category'], {
  limit: 4,
  use : 'mongo-db',
  props: {
    filter: {}//{category: 'All'},
  },
  'query': function(searchString, opts) {
    // Default query that will be used for the mongo-db selector
    var query = EasySearch.getSearcher(this.use).defaultQuery(this, searchString);
    // filter for categories if set
    _.extend(query, this.props.filter)
    return query;
  }
});

function buildRegExp(searchText) {
  // this is a dumb implementation
  var parts = searchText.trim().split(/[ \-\:]+/);
  return new RegExp("(" + parts.join('&') + ")", "ig");
}

Meteor.methods({
  postInsert: function(postAttributes) {
    check(this.userId, String);
    check(postAttributes, {
      title: String,
      cont: String
    });
    
    var errors = validatePost(postAttributes);
    if (errors.title || errors.desc)
      throw new Meteor.Error('invalid-post', "You must set a title and description for your post");
    
    var user = Meteor.user();
    var post = _.extend(postAttributes, {
      userId: user._id, 
      author: user.username, 
      submitted: new Date(),
      commentsCount: 0,
    });
    
    var postId = Posts.insert(post);
    
    return {
      _id: postId
    };
  },
});