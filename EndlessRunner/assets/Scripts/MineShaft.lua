function MineShaft.OnInit()
	this.railPrefab = Prefab.Load("rail.pfb");
	this.gemPrefab = Prefab.Load("GemRail.pfb");
	this.railPrefab:MarkStore();
	this.gemPrefab:MarkStore();

    this.maxDist = 120.0; --furthest rail position
    this.moveSpeed = 10.0;
	this.loopPosition = 0.0;
    this.sectionLength = 12.0;
	this.track = {};
	this.score = 0;
end

function MineShaft.OnEnable()
    math.randomseed(os.time());
    MineShaft.SpawnStartingTrack();
end

function MineShaft.SpawnStartingTrack()
    for i = 0, 10, 1 do
        this.loopPosition = -1 * i * this.sectionLength;
        MineShaft.MakeSegment();
    end
    this.loopPosition = 0.0;
end

function MineShaft.GetRandomRailPrefab()
    if (math.random() > 0.1) then
        return this.railPrefab;
    else
        return this.gemPrefab;
    end
end

function MineShaft.MakeSegment()
    -- spawn row of rails with obstacles
	SpawnRail(-1, 0, MineShaft.GetRandomRailPrefab());
	SpawnRail(0, 0, MineShaft.GetRandomRailPrefab());
	SpawnRail(1, 0, MineShaft.GetRandomRailPrefab());

    --spawn secondary row of rails
    SpawnRail(-1, 1, this.railPrefab);
	SpawnRail(0, 1, this.railPrefab);
	SpawnRail(1, 1, this.railPrefab);
end

function SpawnRail(column, row, prefab)
	local rail = prefab:CreateObject();
	rail:GetTransform().Position = Vector3(5.0 * column, 0.0, this.maxDist + this.loopPosition - (row * this.sectionLength/2) );
    
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
