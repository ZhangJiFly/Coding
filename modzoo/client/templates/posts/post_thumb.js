Template.postThumb.helpers({
  dateAndTime: function() {
    return this.submitted.toLocaleDateString();
  },
   summary: function(){
    return this.content.substring(0, 100) + "..."
  },
});
