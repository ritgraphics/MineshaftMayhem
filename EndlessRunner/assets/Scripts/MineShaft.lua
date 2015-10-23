function MineShaft.OnInit()
	this.railPrefab = Prefab.Load("rail.pfb");
	this.railPrefab:MarkStore();
	this.speed = 5.0;
	this.position = 0.0;
	this.test = 0.0;
	this.track = {};
end

function MineShaft.OnEnable()
end


function MineShaft.MakeSegment()
	local row = {};
	row.left = SpawnRail(-1, this.railPrefab);
	row.middle = SpawnRail(0, this.railPrefab);
	row.right = SpawnRail(1, this.railPrefab);
	this.track[0] = row;
end

function SpawnRail(column, prefab)
	local rail = prefab:CreateObject();
	rail:GetTransform().Position = Vector3(5.0 * column, 0.0, this.test);
	return rail;
end

function MineShaft.Update(dt)
	this.position = this.position + (dt*this.speed);
	this.test = this.test + (dt*this.speed);
	if (this.position > 6.0) then
		this.position = this.position - 6.0;
		MineShaft.MakeSegment();
	end
	
end

function MineShaft.OnDisable()
	
end


function MineShaft.OnDestroy()
	this.railPrefab:MarkDelete();
end
