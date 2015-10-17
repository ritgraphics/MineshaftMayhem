function MineShaft.OnInit()
end

function MineShaft.MakeSegment()

	local railPrefab = Prefab.Load("rail.pfb");
	local rail1 = railPrefab:CreateObject();
	rail1:GetTransform().Position = Vector3(-5.0, 0.0, 0.0);
	
	local rail2 = railPrefab:CreateObject();
	rail2:GetTransform().Position = Vector3(0.0, 0.0, 0.0);
	
	local rail3 = railPrefab:CreateObject();
	rail3:GetTransform().Position = Vector3(5.0, 0.0, 0.0);
	
	rail2:AddChild(rail1);
	rail2:AddChild(rail3);
	
	rail1:Delete();
	
end

function MineShaft.OnEnable()
	
	local numRails = 30;
	local go = this.GameObject;
	MineShaft.MakeSegment();
	
	--[[
	for i=0, numRails, 1
	do
		local rail = railPrefab:CreateObject();

		rail:GetTransform().Position = transform.Position + Vector3(0.0, 0.0, 0.0 + (7.5 * i));
	end

	for i=0, numRails, 1
	do
		local rail = railPrefab:CreateObject();

		rail:GetTransform().Position = transform.Position + Vector3(-5, 0.0, 0.0 + (7.5 * i));
	end
	

	for i=0, numRails, 1
	do
		local rail = railPrefab:CreateObject();

		rail:GetTransform().Position = transform.Position + Vector3(5, 0.0, 0.0 + (7.5 * i));
	end ]]--

	--local rail2 = railPrefab:CreateObject();
	
end



function MineShaft.Update(dt)

	

end

function MineShaft.OnDisable()
	
end


function MineShaft.OnDestroy()
	
end
