(function()
{
define([], function()
{
	var PersonVO = function(first, last)
	{
		return {
			firstName: first,
			lastName: last,
			getPrettyName: function()
			{
				return lastName + "," + firstName;
			}
		};
	};
	return PersonVO;
});
}
)();