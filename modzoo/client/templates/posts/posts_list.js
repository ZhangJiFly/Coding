Template.postsList.created = function() {
  var instance = EasySearch.getComponentInstance(
    { id : 'search', index : 'posts' }
  );

  instance.on('currentValue', function(val){
    Session.set('search', val);
  });
};

Template.postsList.helpers({
  searchVal: function () {
    return Session.get('search');
  },
});


