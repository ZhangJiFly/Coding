sum = 0


def isMultiple(x)
	if x % 3 === 0 || x % 5 ===0
		return true
	else
		return false
	end
end

for i in 0..999
   if isMultiple(i)
   		sum += i
   end
end

puts sum


