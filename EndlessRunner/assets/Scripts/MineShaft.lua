function MineShaft.OnInit()
	this.railPrefab = Prefab.Load("rail.pfb");
	this.railPrefab:MarkStore();
    this.maxDist = 120.0; --furthest rail position
    this.moveSpeed = 10.0;
	this.loopPosition = 0.0;
    this.sectionLength = 6.0;
	this.track = {};
	this.score = 0;
end

function MineShaft.OnEnable()
    MineShaft.SpawnStartingTrack();
end

function MineShaft.SpawnStartingTrack()
    for i = 0, 20, 1 do
        this.loopPosition = -1 * i * this.sectionLength;
        MineShaft.MakeSegment();
    end
    this.loopPosition = 0.0;
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
	rail:GetTransform().Position = Vector3(5.0 * column, 0.0, this.maxDist + this.loopPosition);
    
    local id = rail:GetID();
    local scriptName = "Rail";

    Rail.hash[""..id].manager = this;
    

	return rail;
end

function MineShaft.Update(dt)
    this.moveSpeed = this.moveSpeed + dt * 0.1;
	
	this.score = this.score + (this.moveSpeed * dt);
	print(math.floor(this.score));

	this.loopPosition = this.loopPosition + (dt*this.moveSpeed);
	if (this.loopPosition > this.sectionLength) then
		this.loopPosition = this.loopPosition - this.sectionLength;
		MineShaft.MakeSegment();
	end
	
end

function MineShaft.OnDisable()
	
end


function MineShaft.OnDestroy()
	this.railPrefab:MarkDelete();
end
