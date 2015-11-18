Template.postsList.render = function() {
  var search = Session.get('search');
  $('search-box').val(search);
};