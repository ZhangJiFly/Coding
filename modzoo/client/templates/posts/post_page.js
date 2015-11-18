Template.postPage.helpers({
	hasNext: function(){
		return this.nextPost;
	},
	hasPrevious: function(){
		return this.previousPost;
	},
	comments: function() {
		return Comments.find({postId: this._id});
	},
	dateAndTime: function() {
		return this.submitted.toLocaleDateString();
	},
});