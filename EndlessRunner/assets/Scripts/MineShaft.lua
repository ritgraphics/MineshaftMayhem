function MineShaft.OnInit()
	this.railPrefab = Prefab.Load("rail.pfb");
	this.gemPrefab = Prefab.Load("GemRail.pfb");
	this.brokenPrefab = Prefab.Load("BrokenRail.pfb");
	this.railPrefab:MarkStore();
	this.gemPrefab:MarkStore();
    this.brokenPrefab:MarkStore();
	this.wallPrefab = Prefab.Load("mineSection.pfb");
	this.wallPrefab:MarkStore();

	this.speedBoostPrefab = Prefab.Load("SpeedBoostRail.pfb");
	this.speedBoostPrefab:MarkStore();

    this.maxDist = 120.0; --furthest rail position
    this.moveSpeed = 10.0;
	this.loopPosition = 0.0;
    this.sectionLength = 12.0;
	this.track = {};
	this.score = 0;

	--Speed Boost
	this.boostAmt = 10.0;
	this.boostLife = 0.0;
	this.boostDuration = 0.0;
end

function MineShaft.OnEnable()
    math.randomseed(os.time());
    MineShaft.SpawnStartingTrack();
end

function MineShaft.CalcBoostSpeed(dt)
	if this.boostDuration == 0 or this.boostLife== 0 or this.boostAmt == 0 then
		return 0;
	end

	this.boostLife = this.boostLife - dt;

	if this.boostLife < 0 then
		this.boostLife = 0;
		this.boostDuration = 0;
		this.boostAmt = 0;
		
		return 0;
	end

	return 40;
end

function MineShaft.SpawnStartingTrack()
    for i = 0, 10, 1 do
        this.loopPosition = -1 * i * this.sectionLength;
        MineShaft.MakeSegment();
    end
    this.loopPosition = 0.0;
end

function MineShaft.GetRandomHazardRail()
    local rand = math.random();
    if (rand > 0.0) then
        return this.brokenPrefab;
    end
end

function MineShaft.GetRandomSafeRail()
    local rand = math.random();
    if (rand > 0.95) then
		return this.speedBoostPrefab;
    elseif (rand > 0.5) then
        return this.gemPrefab;
    else
        return this.railPrefab;
	end
end

function MineShaft.MakeSegment()
    -- spawn row of rails with obstacles
    local numHazards = math.random()*math.random()*1.1;
    local startPoint = math.floor(math.random()*3);

    for i = startPoint, startPoint+2, 1 do
        if(numHazards > 0) then
	        MineShaft.SpawnRail((i%3)-1, 0, MineShaft.GetRandomHazardRail());
            numHazards = numHazards - 1;
        else
	        MineShaft.SpawnRail((i%3)-1, 0, MineShaft.GetRandomSafeRail());
        end
    end

    --spawn secondary row of rails
    MineShaft.SpawnRail(-1, 1, this.railPrefab);
	MineShaft.SpawnRail(0, 1, this.railPrefab);
	MineShaft.SpawnRail(1, 1, this.railPrefab);

	-- wall section
	MineShaft.SpawnWall(0, this.wallPrefab);
	MineShaft.SpawnWall(1, this.wallPrefab);
end

function MineShaft.SpawnRail(column, row, prefab)
	local rail = prefab:CreateObject();
	rail:GetTransform().Position = Vector3(5.0 * column, 0.0, this.maxDist + this.loopPosition - (row * this.sectionLength/2) );
    
    local id = rail:GetID();

    Rail.hash[""..id].manager = this;

	return rail;
end

function MineShaft.SpawnWall(row, prefab)
	local wall = prefab:CreateObject();
	wall:GetTransform().Position = Vector3(0.0, 0.0, this.maxDist + this.loopPosition - (row * this.sectionLength/2) );

	local id = wall:GetID();
	MineSection.hash[""..id].manager = this;

	return wall;
end

function MineShaft.Update(dt)
    this.moveSpeed = this.moveSpeed + dt * 0.1;
	
	this.score = this.score + (this.moveSpeed * dt);

	this.loopPosition = this.loopPosition + (dt*(this.moveSpeed));
	if (this.loopPosition > this.sectionLength) then
		this.loopPosition = this.loopPosition - this.sectionLength;
		MineShaft.MakeSegment();
	end
end

function MineShaft.OnDisable()
	
end


function MineShaft.OnDestroy()
	this.railPrefab:MarkDelete();
	this.gemPrefab:MarkDelete();
	this.brokenPrefab:MarkDelete();
	this.wallPrefab:MarkDelete();
	this.speedBoostPrefab:MarkDelete();
end
