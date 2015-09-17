
test = {}

function test.Update(dt)
	go = TEST.GO;
	transform = go:GetTransform();
	transform:RotateY(dt);
end
