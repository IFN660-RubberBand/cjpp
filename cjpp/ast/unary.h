class NUnaryExpression : public NExpression {
public:
	NUnaryExpression* unexpr;
	NUnaryExpression(const NUnaryExpression* u)
	{
		unexpr = u;
	}
};