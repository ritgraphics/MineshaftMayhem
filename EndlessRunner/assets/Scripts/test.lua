

function test.Start()
	print('Start called');
	
	function this.move(dt)
		this.GameObject:GetTransform():TranslateX(dt);
	end
end


function test.Update(dt)
	go = this.GameObject;
	transform = go:GetTransform();
	transform:RotateY(dt);
	this.move(dt);
end

function test.Stop()
	print('Stop called');
end

