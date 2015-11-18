Student.js
(function()
{
define(['jquery'], function($){

	var PersonVO = function(first, last, subject, year){

		return {
			firstName: first,
			lastName: last,
			subject: subject,
			year: year,
			getFullName: function(){

				return lastName + "," + firstName;
			}
		};
	};
	return Student;
});
}
)();