namespace Engine
{
	struct Entity;
	struct Component
	{
		friend Engine::Entity;

	private:
		virtual void Update();
		virtual void PhysicsUpdate();
	};
}