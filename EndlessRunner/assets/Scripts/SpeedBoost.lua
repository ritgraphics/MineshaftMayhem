function SpeedBoost.OnInit()
	
end

function SpeedBoost.OnEnable()
    this.player = Scene.FindObjectWithName("minecart1");
end

function SpeedBoost.Update(dt)
    --static member variable
    if SpeedBoost.mineShaft == nil then
        local obj = Scene.FindObjectWithName("railspawner");
        local id = obj:GetID();
        SpeedBoost.mineShaft = MineShaft.hash[""..id];
	end

	local go = this.GameObject;
	
	local transform = go:GetTransform();

    local distance = transform.WorldPosition - this.player:GetTransform().WorldPosition;
    local distanceSqrd = distance:Z() * distance:Z() + distance:X() * distance:X();

    if distanceSqrd <= 16.0 then
		SpeedBoost.mineShaft.boostAmt = 5;
		SpeedBoost.mineShaft.boostDuration = SpeedBoost.mineShaft.boostDuration + 5;

        go:Delete();
        go = nil;
    end
end

function SpeedBoost.OnDisable()
	
end

function SpeedBoost.OnDestroy()
	
end
