Template.topFive.helpers({
	topFive: function(){
		return Posts.find({}, {sort: {submitted: -1, _id:-1}, limit:5});
	}
})