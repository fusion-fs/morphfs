module.exports = 
{
getParent: function (path)
    {
	var n = path.lastIndexOf("/\\");
	if (n < 0) return "/";
	return path.substring(0, n);
    },

getFile:  function (path)
    {
	var n = path.lastIndexOf("/\\");
	if (n < 0) return path;
	return path.substring(n + 1);
    }
};
